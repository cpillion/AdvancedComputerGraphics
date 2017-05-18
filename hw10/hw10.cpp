/*
 *  OpenCL square matrix transpose
 *
 *  The size of the matrix is width*blocks
 *
 *  Parameters:
 *  -v      Verbose - show hardware detila
 *  width   Block width (width squared <= max threads/block)
 *  blocks  Number of blocks
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

/*
 *  Return elapsed wall time since last call (seconds)
 */
static double t0=0;
float Elapsed(void)
{
#ifdef _WIN32
   //  Windows version of wall time
   LARGE_INTEGER tv,freq;
   QueryPerformanceCounter((LARGE_INTEGER*)&tv);
   QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
   double t = tv.QuadPart/(double)freq.QuadPart;
#else
   //  Unix/Linux/OSX version of wall time
   struct timeval tv;
   gettimeofday(&tv,NULL);
   double t = tv.tv_sec+1e-6*tv.tv_usec;
#endif
   float s = t-t0;
   t0 = t;
   return s;
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Initialize matrix with random values
 */
void RandomInit(float x[],const unsigned int n)
{
   for (unsigned int i=0;i<n*n;i++)
      x[i] = rand() / (float)RAND_MAX;
}

/*
 *  OpenCL notify callback (echo to stderr)
 */
void Notify(const char* errinfo,const void* private_info,size_t cb,void* user_data)
{
   fprintf(stderr,"%s\n",errinfo);
}

/*
 *  Initialize fastest OpenCL device
 */
cl_device_id     devid;
cl_context       context;
cl_command_queue queue;
int InitGPU(int verbose)
{
   cl_uint Nplat;
   cl_int  err;
   char name[1024];
   int  MaxGflops = -1;

   //  Get platforms
   cl_platform_id platforms[1024];
   if (clGetPlatformIDs(1024,platforms,&Nplat))
      Fatal("Cannot get number of OpenCL platforms\n");
   else if (Nplat<1)
      Fatal("No OpenCL platforms found\n");
   //  Loop over platforms
   for (unsigned int platform=0;platform<Nplat;platform++)
   {
      if (clGetPlatformInfo(platforms[platform],CL_PLATFORM_NAME,sizeof(name),name,NULL)) Fatal("Cannot get OpenCL platform name\n");
      if (verbose) printf("OpenCL Platform %d: %s\n",platform,name);

      //  Get GPU device IDs
      cl_uint Ndev;
      cl_device_id id[1024];
      if (clGetDeviceIDs(platforms[platform],CL_DEVICE_TYPE_GPU,1024,id,&Ndev))
         Fatal("Cannot get number of OpenCL devices\n");
      else if (Ndev<1)
         Fatal("No OpenCL devices found\n");

      //  Find the fastest device
      for (unsigned int dev=0;dev<Ndev;dev++)
      {
         cl_uint proc,freq;
         if (clGetDeviceInfo(id[dev],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(proc),&proc,NULL)) Fatal("Cannot get OpenCL device units\n");
         if (clGetDeviceInfo(id[dev],CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(freq),&freq,NULL)) Fatal("Cannot get OpenCL device frequency\n");
         if (clGetDeviceInfo(id[dev],CL_DEVICE_NAME,sizeof(name),name, NULL)) Fatal("Cannot get OpenCL device name\n");
         int Gflops = proc*freq;
         if (verbose) printf("OpenCL Device %d: %s Gflops %f\n",dev,name,1e-3*Gflops);
         if(Gflops > MaxGflops)
         {
            devid = id[dev];
            MaxGflops = Gflops;
         }
      }
   }

   //  Print fastest device info
   if (clGetDeviceInfo(devid,CL_DEVICE_NAME,sizeof(name),name,NULL)) Fatal("Cannot get OpenCL device name\n");
   printf("Fastest OpenCL Device: %s\n",name);

   //  Check thread count
   size_t mwgs;
   if (clGetDeviceInfo(devid,CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(mwgs),&mwgs,NULL)) Fatal("Cannot get OpenCL max work group size\n");

   //  Create OpenCL context for fastest device
   context = clCreateContext(0,1,&devid,Notify,NULL,&err);
   if(!context || err) Fatal("Cannot create OpenCL context\n");

   //  Create OpenCL command queue for fastest device
   queue = clCreateCommandQueue(context,devid,0,&err);
   if(!queue || err) Fatal("Cannot create OpenCL command cue\n");

   return mwgs;
} 


/*
 * C = A' -- host
 */
void transH(float C[], const float A[], unsigned int n)
{
   for (unsigned int i=0;i<n;i++)
      for (unsigned int j=0;j<n;j++)
      {
         //printf("Original Value: %3.2f     ", A[i*n+j]);
         C[i*n+j] = A[j*n+i];
         //printf("Transposed Value: %3.2f \n", C[i*n+j]);

      }
}


/*
* Compute one element of A'
*/
const char* source =
  "__kernel void transA(__global float* C,__global const float* A,const unsigned int n)\n"
  "{\n"
  "   unsigned int j = get_global_id(0);\n"
  "   unsigned int i = get_global_id(1);\n"
  "   C[i*n+j] = A[j*n+i];\n"
  "}\n";

/*
 * C = A' -- device
 */
void transD(float Ch[],float Ah[],const unsigned int Bw,const unsigned int Bn)
{
   //  Calculate matrix dimensions
   unsigned int n = Bw*Bn;
   unsigned int N = n*n*sizeof(float);

   // Allocate device memory and copy A from host to device
   cl_int  err;
   cl_mem Ad = clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,N,Ah,&err);
   if (err) Fatal("Cannot create and copy A from host to device\n");

   //  Allocate device memory for C on device
   cl_mem Cd = clCreateBuffer(context,CL_MEM_WRITE_ONLY,N,NULL,&err);
   if (err) Fatal("Cannot create C on device\n");

   //  Compile kernel
   cl_program prog = clCreateProgramWithSource(context,1,&source,0,&err);
   if (err) Fatal("Cannot create program\n");
   if (clBuildProgram(prog,0,NULL,NULL,NULL,NULL))
   {
      char log[1048576];
      if (clGetProgramBuildInfo(prog,devid,CL_PROGRAM_BUILD_LOG,sizeof(log),log,NULL))
         Fatal("Cannot get build log\n");
      else
         Fatal("Cannot build program\n%s\n",log);
   }
   cl_kernel kernel = clCreateKernel(prog,"transA",&err);
   if (err) Fatal("Cannot create kernel\n");

   //  Set parameters for kernel
   if (clSetKernelArg(kernel,0,sizeof(cl_mem),&Cd)) Fatal("Cannot set kernel parameter Cd\n");
   if (clSetKernelArg(kernel,1,sizeof(cl_mem),&Ad)) Fatal("Cannot set kernel parameter Ad\n");
   if (clSetKernelArg(kernel,2,sizeof(int),&n)) Fatal("Cannot set kernel parameter n\n");

   //  Run kernel
   size_t Global[2] = {n,n};
   size_t Local[2]  = {Bw,Bw};
   if (clEnqueueNDRangeKernel(queue,kernel,2,NULL,Global,Local,0,NULL,NULL)) Fatal("Cannot run kernel\n");

   //  Release kernel and program
   if (clReleaseKernel(kernel)) Fatal("Cannot release kernel\n");
   if (clReleaseProgram(prog)) Fatal("Cannot release program\n");

   // Copy C from device to host (block until done)
   if (clEnqueueReadBuffer(queue,Cd,CL_TRUE,0,N,Ch,0,NULL,NULL)) Fatal("Cannot copy C from device to host\n");

   //  Free device memory
   clReleaseMemObject(Ad);
   //clReleaseMemObject(Bd);
   clReleaseMemObject(Cd);
}

/*
 *  main
 */
int main(int argc, char* argv[])
{
   //  Process options
   int opt;
   int verbose=0;
   while ((opt=getopt(argc,argv,"v"))!=-1)
   {
      if (opt=='v')
         verbose++;
      else
         Fatal("Usage: [-v] <block width> <number of blocks>\n");
   }
   argc -= optind;
   argv += optind;
 
   //  Get width and number of blocks
   if (argc!=2) Fatal("Usage: [-v] <block width> <number of blocks>\n");
   int Bw = atoi(argv[0]);
   if (Bw<1) Fatal("Block width out of range %d\n",Bw);
   int Bn = atoi(argv[1]);
   if (Bn<1) Fatal("Number of blocks out of range %d\n",Bn);
   //  Total width is block times number of blocks
   int n = Bw*Bn;
   int N = n*n*sizeof(float);
   printf("Bw=%d Bn=%d n=%d\n",Bw,Bn,n);

   //  Initialize GPU
   int Mw = InitGPU(verbose);
   if (Mw<Bw*Bw) Fatal("Thread count %d exceeds max work group size of %d\n",Bw*Bw,Mw);

   // Allocate host matrices A/B/C/R
   float* Ah = (float*)malloc(N);
   float* Ch = (float*)malloc(N);
   float* Rh = (float*)malloc(N);
   if (!Ah || !Ch || !Rh) Fatal("Cannot allocate host memory\n");

   // Initialize A
   srand(9999);
   RandomInit(Ah,n);

   //  Computer R = A' on host
   Elapsed();
   transH(Rh, Ah, n);
   float Th = Elapsed();
   
   //  Compute C = A' on device
   Elapsed();
   transD(Ch,Ah,Bw,Bn);
   float Td = Elapsed();

   //  Compute difference between R and C
   double r2=0;
   for (int i=0;i<n*n;i++)
      r2 += fabs(Ch[i]-Rh[i]);
   r2 /= n*n;

   //  Free host memory
   free(Ah);
   free(Ch);
   free(Rh);

   //  Print results
   printf("Host   Time = %6.3f s\n",Th);
   printf("Device Time = %6.3f s\n",Td);
   printf("Speedup = %.1f\n",Th/Td);
   printf("Difference = %.2e\n",r2);

   //  Done
   return 0;
}

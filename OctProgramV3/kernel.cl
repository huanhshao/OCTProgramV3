#define _PI 3.1415926535897
__attribute__((always_inline)) float
logout(float2 in,float k,float a){
	float tmp=(log(length(in)/8+1)-k)*a;
	tmp=tmp>1?1:tmp;
	tmp=tmp<0?0:tmp;
	return tmp;
}
__attribute__((always_inline)) void
twidle_factor(float k,float angle,float2* in){
	float2 tw, v;
	tw.x = cos(k*angle);
	tw.y = sin(k*angle);
	v.x = tw.x*((*in).x) - tw.y*((*in).y);
	v.y = tw.x*((*in).y) + tw.y*((*in).x);
	(*in)=v;
}
__attribute__((always_inline)) void
FFT4(float2* in0, float2* in1, float2* in2, float2* in3){
	float2 v0, v1, v2, v3;
	v0 = *in0 + *in2;
	v1 = *in1 + *in3;
	v2 = *in0 - *in2;
	v3.x = (*in1).y - (*in3).y;
	v3.y = (*in3).x - (*in1).x;
	*in0 = v0 + v1;
	*in2 = v0 - v1;
	*in1 = v2 + v3;
	*in3 = v2 - v3;
}
__attribute__((always_inline)) void
MyWriteImage(__write_only image2d_t img,float4 colors,uint gid,uint lid){
	float4 color=(float4)(colors.x,colors.x,colors.x,1.0);
	int2 coord=(int2)(gid,lid);
	write_imagef(img,coord,color);
	coord.x=gid+256;
	color=(float4)(colors.y,colors.y,colors.y,1.0);
	write_imagef(img,coord,color);
	coord.x=gid+256*2;
	color=(float4)(colors.z,colors.z,colors.z,1.0);
	write_imagef(img,coord,color);
	coord.x=gid+256*3;
	color=(float4)(colors.w,colors.w,colors.w,1.0);
	write_imagef(img,coord,color);
}
__kernel __attribute__((reqd_work_group_size (256,1,1))) void
kfft(__global float* data,__write_only image2d_t img,float k,float a){
	uint gid=get_local_id(0);
	uint lid=get_group_id(1);
	gid=gid&0xffu;

	__local float lds[2048];
	__global float* gr=(__global float*)(data+gid+(lid*1024));
	float2 in0=(float2)((float)gr[0*256]*8,0);
	float2 in1=(float2)((float)gr[1*256]*8,0);
	float2 in2=(float2)((float)gr[2*256]*8,0);
	float2 in3=(float2)((float)gr[3*256]*8,0);

	uint ns=1;
	uint kw=4;
	uint i=0;
	uint idout=0;
	float angle=0;
	for (i=0;i<2;i++){
		if(ns>1){
			angle = -2*_PI*(gid%ns)/(ns*kw);
			twidle_factor(1, angle, &in1);
			twidle_factor(2, angle, &in2);
			twidle_factor(3, angle, &in3);
		}
		FFT4(&in0,&in1,&in2,&in3);
		idout = (gid/ns)*ns*kw+(gid%ns);
		lds[(0*ns)+idout]=in0.x;
		lds[(1*ns)+idout]=in1.x;
		lds[(2*ns)+idout]=in2.x;
		lds[(3*ns)+idout]=in3.x;
		idout=idout+1024;
		lds[(0*ns)+idout]=in0.y;
		lds[(1*ns)+idout]=in1.y;
		lds[(2*ns)+idout]=in2.y;
		lds[(3*ns)+idout]=in3.y;
		barrier(CLK_LOCAL_MEM_FENCE);
		ns=ns*4;
		in0.x=lds[0*256+gid];
		in1.x=lds[1*256+gid];
		in2.x=lds[2*256+gid];
		in3.x=lds[3*256+gid];
		in0.y=lds[4*256+gid];
		in1.y=lds[5*256+gid];
		in2.y=lds[6*256+gid];
		in3.y=lds[7*256+gid];
	}
	for (i=0;i<2;i++){
		if(ns>1){
			angle = -2*_PI*(gid%ns)/(ns*kw);
			twidle_factor(1, angle, &in1);
			twidle_factor(2, angle, &in2);
			twidle_factor(3, angle, &in3);
		}
		FFT4(&in0,&in1,&in2,&in3);
		idout = (gid/ns)*ns*kw+(gid%ns);
		lds[(0*ns)+idout]=in0.x;
		lds[(1*ns)+idout]=in1.x;
		lds[(2*ns)+idout]=in2.x;
		lds[(3*ns)+idout]=in3.x;
		idout=idout+1024;
		lds[(0*ns)+idout]=in0.y;
		lds[(1*ns)+idout]=in1.y;
		lds[(2*ns)+idout]=in2.y;
		lds[(3*ns)+idout]=in3.y;
		barrier(CLK_LOCAL_MEM_FENCE);
		ns=ns*4;
		in0.x=lds[0*256+gid];
		in1.x=lds[1*256+gid];
		in2.x=lds[2*256+gid];
		in3.x=lds[3*256+gid];
		in0.y=lds[4*256+gid];
		in1.y=lds[5*256+gid];
		in2.y=lds[6*256+gid];
		in3.y=lds[7*256+gid];
	}
	angle = -2*_PI*(gid%ns)/(ns*kw);
	twidle_factor(1, angle, &in1);
	twidle_factor(2, angle, &in2);
	twidle_factor(3, angle, &in3);
	FFT4(&in0,&in1,&in2,&in3);

	float4 colors=(float4)(logout(in0,k,a),logout(in1,k,a),logout(in2,k,a),logout(in3,k,a));
	//float4 colors=(float4)(0.0,0.33,0.66,1.0);
	if ((gid+256*3) < get_image_width(img) && (lid) < get_image_height(img)){
		MyWriteImage(img,colors,gid,lid);
	}
}
__kernel __attribute__((reqd_work_group_size (256,1,1))) void
hist(__read_only image2d_t img,__global int* hst,int COUNTN){
	__local int thst[256];
	uint tid=get_local_id(0);
	uint nid=get_group_id(0);
	uint mid=get_group_id(1);

	int w=get_image_width(img);
	int h=get_image_height(img);

	if(tid<256){
		thst[tid]=0;
	}
	barrier(CLK_LOCAL_MEM_FENCE);

	const sampler_t sampler =	CLK_NORMALIZED_COORDS_FALSE	|
								CLK_ADDRESS_CLAMP_TO_EDGE	|
								CLK_FILTER_NEAREST;	
	int i=0;
	int2 coord=(int2)(tid+nid*256,mid*COUNTN);
	float4 clr;
	uchar idx=0;
	for(i=0;i<COUNTN;i++){
		if(coord.x<w && coord.y<h){
			clr=read_imagef(img,sampler,coord);
			idx=convert_uchar_sat(clr.y*255.0f);
			atomic_inc(&thst[idx]);
			coord.y++;
		}
	}
	barrier(CLK_LOCAL_MEM_FENCE);
	
	if(tid<256){
		atomic_add(&hst[tid],thst[tid]);
	}
}
__kernel void
loadimg(__write_only image2d_t dst,__read_only image2d_t src,int i){
	const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE	|
							  CLK_ADDRESS_CLAMP_TO_EDGE		|
							  CLK_FILTER_NEAREST;
	uint xid=get_global_id(0);
	uint yid=get_global_id(1);

	int2 incoord=(int2)(xid,(yid+i)%64);
	int2 outcoord=(int2)(xid,yid);
	if(xid<64&&yid<64){
		float4 tmpColor=read_imagef(src,sampler,incoord);
		write_imagef(dst,outcoord,tmpColor);
	}
}
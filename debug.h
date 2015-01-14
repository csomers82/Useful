#ifdef DEBUG
	#define MISUSE fprintf(stderr, "\nError: improper use of '%s'", __func__);
	#define STAFF fprintf(stderr, "\n================================");
	#define SSEP fprintf(stderr, "\n--------------------------------");
	#ifdef COLOUR
		#define AA 36
		#define BB 32
		#define CC 34
		#define DD 31
		#define EE 35
		#define SHADE  30 // {30-K, 31-R, 32-G, 33-Y, 34-B, 35-M, 36-C, 37-W}
		#define SHADE2 30 // {30-K, 31-R, 32-G, 33-Y, 34-B, 35-M, 36-C, 37-W}
		#ifdef SHOWFILE
			#define FILINF fprintf(stderr, "\n\e[%dm%s", SHADE, __FILE__);
			#define WHERE FILINF fprintf(stderr, "\e[%dm%d\e[%dm {%s}==>\e[0m", SHADE2, __LINE__, SHADE, __func__);
		#else
			#define FILINF fprintf(stderr, "\n");
			#define WHERE FILINF fprintf(stderr, "\e[%dm%d\e[%dm {%s}==>\e[0m", SHADE2, __LINE__, SHADE, __func__);
		#endif	
		#define SHOWi(x,c) WHERE fprintf(stderr,"\e[%dm[%4s] = %d\e[0m", c, #x, x);
		#define SHOWl(x,c) WHERE fprintf(stderr,"\e[%dm[%4s] = %Ld\e[0m", c, #x, x);
		#define SHOWc(x,c) WHERE fprintf(stderr,"\e[%dm[%4s] = %c\e[0m", c, #x, x);
		#define SHOWp(x,c) WHERE fprintf(stderr,"\e[%dm[%4s] = %p\e[0m", c, #x, x);
		#define SHOWs(x,c) WHERE fprintf(stderr,"\e[%dm[%4s] = %s\e[0m", c, #x, x);
	#else	
		#ifdef SHOWFILE
			#define FILINF fprintf(stderr, "\n%s:", __FILE__);
			#define WHERE FILINF fprintf(stderr, "::%s:%d %s==> ", __LINE__, __func__);
		#else
			#define FILINF 
			#define WHERE fprintf(stderr, "\n::%s:%d %s==> ", __LINE__, __func__);
		#endif	
		#define SHOWi(x,c) WHERE fprintf(stderr,"[%4s] = %d", #x, x);
		#define SHOWl(x,c) WHERE fprintf(stderr,"[%4s] = %Ld",#x, x);
		#define SHOWc(x,c) WHERE fprintf(stderr,"[%4s] = %c", #x, x);
		#define SHOWp(x,c) WHERE fprintf(stderr,"[%4s] = %p", #x, x);
		#define SHOWs(x,c) WHERE fprintf(stderr,"[%4s] = %s", #x, x);
	#endif
#else
	#define MISUSE
	#define STAFF
	#define SSEP
	#define SPACE(x)
	#define SHOWi(x,c) 
	#define SHOWl(x,c) 
	#define SHOWc(x,c)
	#define SHOWp(x,c)
	#define SHOWs(x,c) 
	#define AA 
	#define BB 
	#define CC 
	#define DD 
	#define EE
#endif


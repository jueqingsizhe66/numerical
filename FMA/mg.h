
#define NPRE  2
#define NPOST 2
#define NGMAX 15
#define ALPHA 0.001
#define DT 0.005
#define DX 0.01
#define DY 0.01
#define DZ 0.01 
#define SOURCETERM 0.01

void addint(double ***uf, double ***uc, double ***res, int nf);
void copy(double ***aout, double ***ain, int n);
void fill0(double ***u, int n);
void interp(double ***uf, double ***uc, int nf);
void relax(double ***u, double ***rhs, int n);
void resid(double ***res, double ***u, double ***rhs, int n);
void rstrct(double ***uc, double ***uf, int nc);
void slvsml(double ***u, double ***rhs);
void mglin(double ***u, int n, int ncycle);

% John Tramm

% Multi-grid Jacobi Solver

hold off;
dt=.005;
alpha = 1;
n=100;
n_h= n / 10;
dx = 4/n;
w = 1.05;

C = alpha*dt/dx^2;

c1 = -C*ones(n,1);
c1_h = -C*ones(n_h,1);

c2 = (2*C+1)*ones(n,1);
c2_h = (2*C+1)*ones(n_h,1);

A=spdiags([c1 c2 c1],-1:1,n,n);
A_h=spdiags([c1_h c2_h c1_h],-1:1,n_h,n_h);

D = diag(diag(A));
D_h = diag(diag(A_h));

invD = diag(1./diag(D));
invD_h = diag(1./diag(D_h));

I = eye(n);
I_h = eye(n_h);

z=transpose(linspace(-2,2,n));
z_h=transpose(linspace(-2,2,n_h));

SWEEPS = 75;
MAX_ITER=1000;
nsteps = 200;
xold = exp(-2*z.^2);
xold_h = exp(-2*z_h.^2);
xnew = exp(-2*z.^2);
xnew_h = exp(-2*z.^2);
threshhold = 1.e-6;

for i=1:nsteps
    %strcat('step ',int2str(i))
    x = xold;
    niter=0;
    
    % Step 1 - A few Jacobi sweeps on the fine grid
    for k=1:SWEEPS
        xnew = (I - w*invD*A)*x + invD*xold;
        e = mean(abs(x-xnew));
        if (e < threshhold) 
            break;
        end
        x = xnew;
    end
    
   
    % Step 2 - Compress fine grid into the coarser grid.
    % This is done using local averages.
    r = 1;
    tmp = 0;
    for m=1:n
        tmp = tmp + x(m);
        if( rem(m,n_h) == 0 )
            xold_h(r) = tmp;
            r = r + 1;
            tmp = 0;
        end
    end
        
    x_h = xold_h;
    
       
    % Step 3 - Run Jacobi on the coarse grid until convergence.
    for k=1:MAX_ITER
        xnew_h = (I_h - w*invD_h*A_h)*x_h + invD_h*xold_h;
        e = mean(abs(x_h-xnew_h));
        if (e < threshhold) 
            break;
        end
        x_h = xnew_h;
    end
    
      
    % Step 4 - Interpolate coarse grid back out to fine grid.
    r = 1;
    x(1) = 0;
    x(n) = 0;
    for m=2:n-1
        if( mod(m,n_h) == 0 )
            r = r+1;
        end
        if( r == n_h )
            x(m) = x_h(r) + ( m - (r-1)*n_h ) * ( x_h(r) + 0 ) / n_h;
        else
            x(m) = x_h(r) + ( m - (r-1)*n_h ) * ( x_h(r) + x_h(r+1) ) / n_h;
        end
      
    end
    
        
    %Step 5 - A few more Jacobi Sweets on the fine grid.
    for k=1:SWEEPS
        xnew = (I - w*invD*A)*x + invD*xold;
        e = mean(abs(x-xnew));
        if (e < threshhold) 
            break;
        end
        x = xnew;
    end
    
 
    plot(z,x);
    axis manual;
    axis([-2 2 0 1]);
    drawnow;
    
      
    xold=x;
end

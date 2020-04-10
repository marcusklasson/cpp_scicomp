close all;
path = pwd;
fileID = fopen([path, '/grid.bin'], 'r');
m = fread(fileID, 1, 'int');
n = fread(fileID, 1, 'int');
G = fread(fileID, [(m+1)*(n+1), 2], 'double');
fclose(fileID);

fileID = fopen([path, '/dux.bin'], 'r');
m1 = fread(fileID, 1, 'int');
n1 = fread(fileID, 1, 'int');
dudx = fread(fileID, [m1, n1], 'double');
fclose(fileID);

fileID = fopen([path, '/duy.bin'], 'r');
m1 = fread(fileID, 1, 'int');
n1 = fread(fileID, 1, 'int');
dudy = fread(fileID, [m1, n1], 'double');
fclose(fileID);

fileID = fopen([path, '/laplace.bin'], 'r');
m1 = fread(fileID, 1, 'int');
n1 = fread(fileID, 1, 'int');
L = fread(fileID, [m1, n1], 'double');
fclose(fileID);
%%
figure()
plot(G(:,1), G(:,2), '*')
xlabel('x'); ylabel('y');

%%
X = vec2mat(G(:,1),m+1)';
Y = vec2mat(G(:,2),m+1)';
U = sin(0.01*X.^2).*cos(0.1*X) + Y;

figure()
surf(X,Y,U);
colorbar
xlabel('x'); ylabel('y'); zlabel('u(x, y)');

%% 
figure()
dudx_true = 0.02.*X.*cos(0.01*X.^2).*cos(0.1*X) - 0.1.*sin(0.01*X.^2).*sin(0.1*X);
surf(X,Y,dudx_true);
colorbar
xlabel('x'); ylabel('y'); zlabel('true du/dx');

%%
figure()
surf(X,Y,dudx');
colorbar
xlabel('x'); ylabel('y'); zlabel('du/dx');
err = abs(dudx_true - dudx');
err = mean(err(:))

%%
figure()
dudy_true = ones(size(duy'));
surf(X,Y,dudy_true);
colorbar
xlabel('x'); ylabel('y'); zlabel('true du/dy');

%%
figure()
surf(X,Y,dudy');
colorbar
xlabel('x'); ylabel('y'); zlabel('du/dy');
err = abs(dudy_true - dudy');
err = mean(err(:))

%%
figure()
surf(X,Y,L');
colorbar
xlabel('x'); ylabel('y'); zlabel('Laplacian \Delta u');


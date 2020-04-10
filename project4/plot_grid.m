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
dux = fread(fileID, [m1, n1], 'double');
%dux = fread(fileID, [m1 * n1, 2], 'double');
fclose(fileID);

fileID = fopen([path, '/duy.bin'], 'r');
m1 = fread(fileID, 1, 'int');
n1 = fread(fileID, 1, 'int');
duy = fread(fileID, [m1, n1], 'double');
fclose(fileID);

fileID = fopen([path, '/laplace.bin'], 'r');
m1 = fread(fileID, 1, 'int');
n1 = fread(fileID, 1, 'int');
L = fread(fileID, [m1, n1], 'double');
fclose(fileID);
%%
figure()
plot(G(:,1), G(:,2), '*')
%xlim([-10.5, 5.5]); ylim([-0.5, 3.5]);
xlabel('x'); ylabel('y');

%%
X = vec2mat(G(:,1),m+1)';
Y = vec2mat(G(:,2),m+1)';
Z = sin(0.01*X.^2).*cos(0.1*X) + Y;

figure()
surf(X,Y,Z);
xlabel('x'); ylabel('y'); zlabel('Z');

%% 
figure()
Zdx = 0.02.*X.*cos(0.01*X.^2).*cos(0.1*X) - 0.1.*sin(0.01*X.^2).*sin(0.1*X);
surf(X,Y,Zdx);
colorbar
%xlim([-10.5, 5.5]); ylim([-0.5, 3.5]);
xlabel('x'); ylabel('y'); zlabel('dZ/dx');

%%
figure()
surf(X,Y,dux');
colorbar
xlabel('x'); ylabel('y'); zlabel('du/dx');
err = abs(Zdx - dux');
err = mean(err(:))

%%
figure()
Zdy = ones(size(duy'));
surf(X,Y,Zdy);
colorbar
xlabel('x'); ylabel('y'); zlabel('dZ/dy');

%%
figure()
surf(X,Y,duy');
colorbar
xlabel('x'); ylabel('y'); zlabel('du/dy');
err = abs(Zdy - duy');
err = mean(err(:))

%%
figure()
surf(X,Y,L');
colorbar
xlabel('x'); ylabel('y'); zlabel('Laplace');


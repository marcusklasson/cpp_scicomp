path = pwd;
fileID = fopen([path, '/outfile.bin'], 'r');
m = fread(fileID, 1, 'int');
n = fread(fileID, 1, 'int');
G = fread(fileID, [(m+1)*(n+1), 2], 'double');
fclose(fileID);
plot(G(:,1), G(:,2), '*')
xlim([-10.5, 5.5]); ylim([-0.5, 3.5]);
xlabel('x'); ylabel('y');
N = 10;
FILE = 'err_from_len.txt';

DATA = fopen(FILE,'r');
if DATA < 0, error('Cannot open file'); end

data = fscanf(DATA, '%e, %f', [2 N]);
res = integral(@f, 0, 3);
data(2,:) = abs(data(2,:) - res);
figure
plot(log2(data(1,:)), log2(data(2,:)),'b')

title('Real error on the length of the segment');
xlabel('Length, log_2');
ylabel('Error, log_2');
axis tight;

fclose(DATA);
N = 10;
FILE = 'err_from_eps.txt';

DATA = fopen(FILE,'r');
if DATA < 0, error('Cannot open file'); end

data = fscanf(DATA, '%e, %f', [2 N]);
res = integral(@f, 0, 3);
data(2,:) = abs(data(2,:) - res);
figure
loglog(data(1,:), data(2,:),'b');
hold on;
loglog(data(1,:), data(1,:),'--');

title('Real error on the given accuracy (in log_{10} scale)');
legend('Error', 'Bisection');
xlabel('Accuracy');
ylabel('Error');
axis tight;

fclose(DATA);
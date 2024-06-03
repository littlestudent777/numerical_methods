N = 10;
FILE = 'it_from_eps.txt';

DATA = fopen(FILE,'r');
if DATA < 0, error('Cannot open file'); end

data = fscanf(DATA, '%e, %d', [2 N]);
figure
semilogx(data(1,:), data(2,:),'b-o');

title('Number of iterations on the given accuracy');
xlabel('Accuracy');
ylabel('Iterations');

fclose(DATA);
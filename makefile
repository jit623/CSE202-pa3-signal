CFLAGS = -g -Wall -Wextra -Wwrite-strings

# Runs prog3 with 4 and with 16 children; each run is scored out of 20 (total 40).
# timeout stops a run that hangs (e.g. a child stuck in pause()) so the score is still reported.
test:
	gcc $(CFLAGS) -DNUMCHILDREN=4 -oprog3 prog3.c
	timeout 60 ./prog3 2>&1 | tee output_4
	gcc $(CFLAGS) -DNUMCHILDREN=16 -oprog3 prog3.c
	timeout 60 ./prog3 2>&1 | tee output_16
	perl ./checkOutput.pl output_4 4 output_16 16

clean:
	rm -f output* prog3

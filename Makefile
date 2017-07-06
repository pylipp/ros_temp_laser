all:
	platformio -f -c -vim run

upload:
	platformio -f -c -vim run -t upload

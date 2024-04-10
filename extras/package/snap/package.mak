snap:
<<<<<<< master
	export SNAPCRAFT_BUILD_INFO=1
=======
	snapcraft prime
>>>>>>> origin/3.0.x
	snapcraft snap

snap-clean:
	snapcraft clean
	rm -rf snap

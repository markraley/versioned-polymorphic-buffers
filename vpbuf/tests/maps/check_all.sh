echo 'comparing maps_A'
diff python/out/maps_A.dat cpp/out/maps_A.dat
diff python/out/maps_A.dat nodejs/out/maps_A.dat

echo 'comparing maps_B'
diff python/out/maps_B.dat cpp/out/maps_B.dat
diff python/out/maps_B.dat nodejs/out/maps_B.dat

echo 'comparing maps_C'
diff python/out/maps_C.dat cpp/out/maps_C.dat
diff python/out/maps_C.dat nodejs/out/maps_C.dat

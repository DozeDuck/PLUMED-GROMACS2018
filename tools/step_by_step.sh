PLUMED-Metadynamic Simulation:#####################################

source ~/workspace/gromacs2023-plumed/bin/GMXRC
export PATH=$HOME/workspace/gromacs2023-plumed/bin:$PATH

# normal procedure
# pdb2gmx
# box
# solv
# ions
# em
# index for complex
# nvt
# npt
# gmx trjconv -f npt.gro -s npt.gro -o npt.pdb
# md 50-100 ns

nohup gmx_plumed mdrun -deffnm md -cpi md.cpt -plumed plumed_tempered.dat -v &

nohup ~/workspace/PLUMED/plumed-gromacs2020/gromacs_plumed_gpu/bin/gmx mdrun -deffnm md -plumed torsion_Ile.dat -v &

# generet fes.dat
plumed sum_hills --hills HILLS
plumed sum_hills --hills HILLS --stride 100 --mintozero

# plumed sum_hills --hills HILLS --idw p1.sss --kt 0.6 --stride 5000 (--nohistory --sigma 0.1 --negbias)

python fes-plot.py

conda activate PLUMED-ISDD-tutorial

gnuplot> p "COLVAR" u 1:2

gnuplot>set pm3d map
gnuplot>splot "fes.dat" w pm3d

gnuplot> p "COLVAR" u 1:2
gnuplot> p "HILLS" u 1:6

gnuplot -e "set terminal png size 800,600; set output 'xyz.png'; p 'good_torsion_Ile_biasfactor10_sigma0.05_HILLS' u 1:6"
gnuplot -e "set terminal png size 800,600; set output 'ramachandran.png'; set pm3d map; splot 'fes.dat' w pm3d"

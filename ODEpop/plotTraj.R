library(ggplot2)
library(cowplot)
library(tidyr)

args <- commandArgs(trailingOnly=TRUE )

csvFile <- args[1]
pngFile <- sub(".csv$",".png",csvFile)

traj <- read.csv(csvFile)
x <- traj[,1]

png(pngFile)

trajt=gather(traj,key="clone",value="size",-t)
output=ggplot(data=trajt,aes(x=t,group=clone,color=clone,y=size))+geom_point()+scale_color_brewer(type="qual")
outputlog=ggplot(data=trajt,aes(x=t,group=clone,color=clone,y=size))+geom_point()+scale_color_brewer(type="qual")+scale_y_log10()
outputgrid=plot_grid(output,outputlog,labels="AUTO",ncol = 2)
save_plot(filename = pngFile,outputgrid,base_width = 16)

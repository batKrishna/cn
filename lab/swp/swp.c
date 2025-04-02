#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
void stop() {
int i = 0, f, ack,l;
printf("Enter the number of frames: ");
scanf("%d", &f);
while (i < f) {
printf("Frame %d is transmitted.\n", i);
sleep(1);
printf("Enter the acknowledgement: ");
scanf("%d", &ack);
if ((ack - 1) == i)
i++;
}
if (ack == f)
{
printf("All frames are transmitted!!!\n");
}
}
void goback(){
int i = 0, f, ack=0, w, sent = 0;
printf("Enter the window size: ");
scanf("%d", &w);
printf("Enter the number of frames: ");
scanf("%d", &f);
while (1) {
for (i = 0; i < w; i++){
if(sent<f){
printf("Frame %d is transmitted.\n",
sent);
sleep(1);
sent++;
}
}
printf("Enter the last acknowledgement: ");
scanf("%d", &ack);
if (ack == f){
printf("All frames are transmitted!!!\n");
break;
}
else
sent = ack;
}
}
void slrp(){
int i = 0, f, ack, w, sent = 0;
printf("Enter the window size: ");
scanf("%d", &w);
printf("Enter the number of frames: ");
scanf("%d", &f);
while (1) {
for (i = 0; i < w; i++) {
if(sent<f){
printf("Frame %d is transmitted.\n",
sent);
sleep(1);
sent++;
}
}
printf("Enter the frame with no
acknowledgement or negative
acknowledgement: ");
scanf("%d", &ack);
if (ack == f){
printf("All frames are transmitted!!!\n");
break;
}
else if((ack-1)==sent)
printf("There is no frame with negative
acknowledgement.\n ");
else {
printf("Frame %d is retransmitted.\n",
ack);
}
}
}
void main() {
int choice;
while (1) {
printf("Sliding Window Protocols Menu:\
n1. Stop-and-Wait\n2. Go-Back-N\n3. Selective
Repeat\n4.Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
if (choice == 1)
stop();
else if (choice == 2)
goback();
else if (choice == 3)
slrp();
else
break;
}
}
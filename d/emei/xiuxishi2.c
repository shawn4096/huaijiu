// xiuxishi2.c 
// ��Ϣ��
inherit ROOM;
#include <room.h>
void create()
{
	set("short", "��Ϣ��");
	set("long",@long
�����Ƕ��ұ����µ���Ϣ�ҡ���������������������������˺ܶ�ľ����
�м���ҹ�����ֵ�Сʦ̫����˯����
long);
	set("exits",([
	    "west" : __DIR__"daxiongdian",
]));
	set("sleep_room", 1);
	set("coor/x",-180);
  set("coor/y",-120);
   set("coor/z",20);
   setup();
}

 // /u/beyond/hz/shanlu3.c ɽ·
 
inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long", @LONG
������ɽ·�ϣ�ɽ·������ľ���̣����ﻰ�㣬ɽ·������һ��Ƭ����
�де����֡�����ǰ�߾��Ǻ��ݵؽ��ˡ�
LONG
        );
set("outdoors","hz");
        set("exits", ([
        "east" : __DIR__"liulin",
        "west" : __DIR__"liulin",
        "north" : __DIR__"shanlu1",
        "south" : __DIR__"qsddao7",
         ]));
        set("coor/x",100);
  set("coor/y",-290);
   set("coor/z",0);
   setup();
}

// Room: /d/xingxiu/xxhh3.c ���޺�
// by shang 97/6

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "���޺�");
        set("long", @LONG
���������޺�����Բ�����ﶼ��һ���޼ʵĺ��������󣬵���
�����˳�֮Ϊ��������Ҳ��������ʪ�����深ֳ���������޵��ӳ���
�˲�׽���棬�Ա�����֮�á�����ͨ�����޺������
LONG);
       
        set("exits", ([
                "east" : __DIR__"xxh1",
                "south" : __FILE__,
                "west" : __DIR__"xxh4",
                "north" : __DIR__"xxh2",
        ]));

        set("outdoors", "xingxiuhai");

        set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",170);
   set("coor/z",0);
   setup();

}
#include "/d/xingxiu/xxh.h";

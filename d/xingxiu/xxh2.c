// Room: /d/xingxiu/xxhh2.c ���޺�
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
                "east" : __DIR__"xxh4",
                "south" : __FILE__,
                "west" : __DIR__"xxh1",
                "north" : __DIR__"xxh3",
        ]));

        set("outdoors", "xingxiuhai");

        set("coor/x",-300);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",160);
   set("coor/z",0);
   setup();

}
#include "/d/xingxiu/xxh.h";

// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺӰ�կ��");
	set("long", @LONG
����һ������׳�۵�կ�ţ����и߹���һ���д�š��ƺӰ
�������֡�կ�����ĸ߹ң���ģ��С���ƺӰ��ǻƺ��ذ���һ�����ᣬ
ƽ�շ�����裬��ѹ���գ������ˡ�����ɳͨ���书��տ����������
���������̺��������˵ȸ��ֽύ��������ƺƴ󡣾���������˹��ᣬ
������������
LONG );
	set("exits", ([
		"east"  : __DIR__"huanghe1",
		"west"  : __DIR__"guangchang",
        "southdown" : __DIR__"caishichang",
	]));
	set("objects", ([
		__DIR__"npc/ma" : 1,
		__DIR__"npc/shen" : 1,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",110);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}


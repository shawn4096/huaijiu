// BY XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
��������߰�����ֻ������ͷ���ϴ���һЩ�����������ż����ï
�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���ζ�����ᴫ��Ұ
�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ���
LONG );
	set("exits", ([
		"east"  : __DIR__"shulin5",
                "north"  : __DIR__"fendi",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",70);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}


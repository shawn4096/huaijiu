// by xiaoyao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��ɽϿ");
	set("long", @LONG
��ɽϿ�Ǹ��ǳ��վ���Ͽ�ȣ���������ʮ�ɵĻ����£����Ƕ��ͣ���
��ֻ��һ������ͨ��һ��һ���խ�����׳ơ�һ���족������û��ʲô��
�ȴ�����ó�������ʧ�١�
LONG );
	set("exits", ([
		"north"     : __DIR__"shimen",
		"south"     : __DIR__"jingyuan",
	]));
	set("objects", ([
		__DIR__"npc/mazei" : 1,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",100);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}


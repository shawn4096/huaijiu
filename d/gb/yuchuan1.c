// yuchuan1.c ؤ���洬

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","�洬");
	set("long", @LONG
�洬������һ�룬���Ҷ�������һģһ���ģ�������ͷ���ۻ�����Ȼ
һ������ӿ������һ�����ȣ����������������㼸�������˺�ȥ��
LONG
	);
	set("exits", ([
	"north" : __FILE__,
	"west" : __FILE__,
	"south" : __DIR__"yugang",
	"east" : __DIR__"yuchuan5",
	]));
	set("coor/x",120);
  set("coor/y",-470);
   set("coor/z",10);
   setup();
}


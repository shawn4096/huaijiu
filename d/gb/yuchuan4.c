// yuchuan4.c ؤ���洬

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
	"west" : __FILE__,
	"north" : __FILE__,
	"east" : __DIR__"yugang",
	"south" : __DIR__"yuchuan5",
	]));
	setup();
}


// yuchuan2.c ؤ���洬

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
	"south" : __FILE__,
	"west" : __FILE__,
	"east" : __DIR__"yugang",
	"north" : __DIR__"yuchuan3",
	]));
	setup();
}


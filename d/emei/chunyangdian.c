// Room: /d/emei/chunyangdian.c

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short",HIR "������" NOR);
	set("long", @LONG
�������һǧ���ף������ľ�Դ䣬�ľ����ˡ���ǰ��һʯ��������ʯ��
��˵����������ɽʱ������������Ϣ�����ڴ˿��ݹ۶�����壬�����𶥣���
���ͱڣ�������ߡ�������������ˮ�֣������ǹ��Ƹ�
LONG
	);
	set("outdoors", "��üɽ");
	set("exits", ([ 
	  "eastdown" : __DIR__"guiyunge",
	  "westup" : __DIR__"shenshuian",
]));
	set("no_clean_up", 0);

	setup();
}

// Room: /d/huashan/path1.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
	set("short", "ɽ����");
	set("long", @LONG
�����ǻ�ɽ���£�����������С�������µ�һɽ����������ɽ����ɽ��
��Զ������һ��������������������ʱ���������롸����ͨ���������и�С
��ׯ�������м��䷿�ݡ�
LONG
	);

	set("exits", ([
	"west" : "/d/village/eexit",
	"north" : __DIR__"yuquan",
	"southeast" : __DIR__"shaluo",
	"south" : __DIR__"shulin",
	]));

	set("outdoors", "��ɽ" );

	set("coor/x",40);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

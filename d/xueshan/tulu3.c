// Room: tulu3.c

inherit ROOM;

void create()
{
	set("short", "�ر���·");
	set("long", @LONG
�����Ѿ����������أ�����Խ��Խ�ߣ�����ϡ����������������������
���������ۣ�ɹ����Ƥ���������ڸ����ңң����Զ��һ���ǳأ���
�˲��ɵ���ܾ��񣬼ӿ��˽Ų���
LONG
	);

	set("exits", ([
		"northeast" : __DIR__"tulu2",
		"west" : __DIR__"mingxiamen",
	]));
        set("outdoors", "ѩɽ");
	set("coor/x",-210);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

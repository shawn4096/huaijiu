// Room: /d/city/xidajie3.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣������һƬ��ɫ��¥����
��Լ�����������Ц���Ǿ����������������񷻡�����������������һ������
�Ĺ㳡����������������ˡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
	        "east" : __DIR__"guangchangbei",
	        "west" : __DIR__"xidajie2",
		"north" : __DIR__"mingyufang",
		"south" : __DIR__"guangchangxi",
	]));

	set("objects", ([
		__DIR__"npc/liumang": 1,
	]) );
	set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "north" && (int)me->query("age") < 14 && !wizardp(me))
		return notify_fail("С���Ѳ�Ҫ�����ֵط�ȥ����\n");
        return ::valid_leave(me, dir);
}

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
    ������������ϣ��е�����Ľ���Ҫ�ȱ𴦵ĸɾ������ࡣ�����
Ϊ�������š���Ӫ���ܱ�����Ե�ʣ������Ƕ�ϲ��ס��������߾����ĵ�
û�м������ˣ�������������ͨ�����⡣�ϱ�������ۣ�������һ�����á�
LONG
	);
        set("outdoors", "city");                
        set("objects",([
        __DIR__"npc/girl" : 1,
        ]));                                                
	set("exits", ([
		"east" : __DIR__"xidajie1",
		"south" : __DIR__"xuanmiaoguan",
		"west" : __DIR__"westgate",
"north" : __DIR__"shuchang",
	]));

	set("coor/x",90);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}


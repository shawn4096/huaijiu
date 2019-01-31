// Room: /d/city/ymdongting.c

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
���������ŵ����ã����϶����������ס������һ������������������ϸ
��������ǽ������һ�����ң����顰����������ĸ���������Ĵ��֡�������
�����ְֳ��Ӳ������ԣ���͢��������֪���Գ�֮�������İ����������飬ʦ
ү�����ں�
LONG
	);

	set("exits", ([
		"east" : __DIR__"dongting",
		"west" : __DIR__"xiting",
                "south" : __DIR__"menlang",
                "northwest" : __DIR__"fyhouyuan",
	]));
	set("objects", ([
		__DIR__"npc/zhao" : 1,
        	__DIR__"npc/shiye" : 1,
        	__DIR__"npc/dayayi" : 1,
	]));

   	set("coor/x",100);
  	set("coor/y",20);
   	set("coor/z",0);
   setup();
}
int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("da yayi", environment(me))) && 
                dir == "northwest")
                return notify_fail("����Ժ�����Ҵ�����������һ����ס���㡣\n");
        return ::valid_leave(me, dir);
}


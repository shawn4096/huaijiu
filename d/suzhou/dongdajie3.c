inherit ROOM;
void create()
{
	set("short", "�����");
	set("long", @LONG
	�����ڶ�����ϣ����ż�ʵ����ʯ����档�����Ƕ���ֵ���
�죬���������ݳ���һ�����ֺŵĵ��̣�������һ��С��ͬ��
LONG
	);
        set("outdoors", "suzhou");    
        set("objects",([
        __DIR__"npc/kid" : 2,
        ]));
        	set("exits", ([
		"east" : __DIR__"dongdajie2",
		"southwest" : __DIR__"baodaiqiao",
		"northwest" : __DIR__"canglangting",
		"north" : __DIR__"hutong",
                "south" : __DIR__"baoheji",
	]));
	set("coor/x",120);
  set("coor/y",-220);
   set("coor/z",0);
   setup();
}


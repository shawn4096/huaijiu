// Room: dating.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "�︮����");
	set("long", @LONG
������Ƿ︮�Ĵ��������ɷǷ���װ���ݻ�������һ��̫ʦ�Σ�����
һ�Ż��º��ƵĻ�Ƥ��������������̫ʦ���ϣ�����������Ե�ʦү�ֹ�
�š���Ƥ���Ա�����������ʯ���磬�������ĳ߸ߣ�ʯ��ɽˮľʯ������
�ǻ�������һ�㡣
LONG
	);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"dayuan",
            "south" : __DIR__"shufang",
]));

        set("objects", ([
            __DIR__"npc/dashou" : 2,
            __DIR__"npc/he" : 1,
]));

	set("coor/x",30);
  set("coor/y",-550);
   set("coor/z",0);
   setup();
}

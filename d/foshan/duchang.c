// Room: /d/fuoshan/duchang.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "Ӣ�ۻ��");
	set("long", @LONG
������һ���ưܵ����������д�š�Ӣ�ۻ�ݡ��ĸ����֡���ȥ��
��ֻ�������Χ�ź�ѹѹ��һ���ˣ�����������Ѻ��С������ոտ���
һ�Σ��еĶĿ����ڻ������еĶĿʹ�ͷɥ����
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"xijie",
]));

        set("objects", ([
        __DIR__"npc/kuang-baoguan" : 1,
]));

	set("no_clean_up", 0);

	set("coor/x",-10);
  set("coor/y",-540);
   set("coor/z",0);
   setup();
}

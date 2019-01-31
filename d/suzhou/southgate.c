// Room: /city/nanmen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
�����ϳ��ţ���ǽ�������˹���ƣ������˻������̸��и�ҵ�Ĺ�棬
�ٸ��ĸ�ʾ(gaoshi)��˲�̫��Ŀ���ٱ��Ǳ������Ļ���Ц�����������ƺ�
���Ǻ�������ִ�ڡ�һ����ֱ����ʯ�������ϱ��������졣
LONG
	);
        
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("outdoors", "suzhou");
           set("exits",([
                "north" : __DIR__"nandajie2",
                "south" : __DIR__"qsgdao2",
           ]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));

	set("coor/x",110);
  set("coor/y",-260);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��֪��\n";
}


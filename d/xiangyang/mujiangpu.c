// Room: /d/xiangyang/mujiangpu.c

inherit ROOM;

void create()
{
	set("short", "ľ����");
	set("long", @LONG
����һ�Ҽ�ª��ľ���̣�һ������ľ�������ڵ��϶�������ֵ��������ľ
����Ҳֻ������Щ��ǹ����ʲô�������Һ��ڡ����Ϻ�ǽ�����ҵضѷ���һЩ
ľ����ľ����ľ��ʲô�ģ����м�������ӣ�����һ���ľ�����ߡ�
LONG
	);

	set("exits", ([
		"north" : __DIR__"eroad1",
	]));

        set("objects", ([
                __DIR__"npc/mujiang" : 1,
        ]));
        set("no_clean_up", 0);

   set("coor/x",10);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}


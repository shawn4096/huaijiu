// Room: /d/village/zahuopu.c

inherit ROOM;

void create()
{
        set("short", "�ӻ���");
	set("long", @LONG
����һ��СС���ӻ��꣬ǽ�ǰ���һ�ѶѵĻ����ɽ���οͿ���������
Щ��ɽ��Ʒ��ǽ�����Ÿ����ӣ��Ǹ���Ŀ��(sign)��
LONG
        );
        set("exits", ([
	"south" : __DIR__"shilu4",
]));
        set("item_desc", (["sign" :
        "������д����
	����(stick)	һ����
	��Ь(shoes)	һ����ʮ��
	ˮ��(bottle)	һ����

	���� Ƥ��(egg) ��ʮ��\n"
]));

        set("no_clean_up", 0);

        set("objects", ([
	                __DIR__"npc/xiaofan": 1
        ]) );

        set("coor/x",10);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}
 
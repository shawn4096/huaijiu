// Room: /city/chaguan.c

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�������ݳ��ϵ�һ�Ҳ�ݡ�һ�߽��������ŵ�һ�ɲ���������Ƣ����ľ�
��Ϊ֮һˬ�����Ű�����һ���ſ��������˿��ˣ������̸Ц����ͷ�Ӷ���
���Ϲ���һ������(zitie) ���������һ˵��֮�ˣ���������־��ˮ䰴�����
��Ӣ�Ҵ��ȵ�Ӣ�۹��¡��販ʿ����ߺ�����к�����, �ݲ���ˮ, æ�Ĳ�����
����
LONG
	);
	set("resource/water", 1);

	set("exits", ([
		"east" : __DIR__"nandajie2",
	]));

        set("item_desc", ([
		"zitie" : "ʮ��һ�������Σ�Ӯ����¥��������\n"
        ]));
	set("objects", ([
		__DIR__"npc/boshi" : 1,
		__DIR__"npc/shuren" : 1,
	]));

	set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   setup();
}


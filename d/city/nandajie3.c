// Room: /d/city/nandajie3.c

inherit ROOM;

void create()
{
	set("short", "�ϴ��");
	set("long", @LONG
�ϴ���������ݳ���ķ����ضΣ�һ�����ϣ�һ�ɵƺ���̣���Ϊ���֡�
Ц�������������������������һƬ��������Ķ��䣬�㲻����Գ��������
�ʹ�ͣ������һ������������һ�����ֵĹ㳡��������һƬ�����������š�һ
��һʮ������Ǯ����ԭ�������Ƿ�Բǧ��֮������һ�Ҷĳ���
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"east" : __DIR__"guangchangnan",
		"south" : __DIR__"nandajie2",
		"west" : __DIR__"duchang",
	        "north" : __DIR__"guangchangxi",
	]));

        set("objects", ([
                __DIR__"npc/dizi4" : 1,
                __DIR__"npc/dizi1" : 1,
        ]));
	set("coor/x",100);
  set("coor/y",-20);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-20);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-20);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-20);
   set("coor/z",0);
   setup();
}


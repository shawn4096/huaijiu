// Room: /d/fuzhou/beimen.c

inherit ROOM;
string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǹ��ݵı��š��������򱱿ɵֽ���һ�������ŵ�ǽ������
��һֽ��ʾ(gaoshi)��
LONG
	);

	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));

	set("exits", ([
                "north" : __DIR__"road5",
                "south" : __DIR__"zhongxin",
	]));

	set("outdoors", "����");
	set("coor/x",100);
  set("coor/y",-460);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
 	return FINGER_D->get_killer() + "\n����Ѳ��\n��˴��\n";
}
// Room: yingmen.c

inherit ROOM;

void create()
{
	set("short", "Ӫ��");
	set("long", @LONG
��ǰ��ԭ�ϳ���һƬ�ɹ�����������¹��Ѿ�Χ����Ӫկ�����ߴ�������
�ĺŽ�������Զ���и�Ӫ�ţ�һ�Ӷӵ��ɹ������������������Ӫ�������Ѿ�ע
�⵽���ˣ�����û��ǸϿ��뿪Ϊ�

LONG
	);

	set("exits", ([
		"north" : __DIR__"jifengying",
		"south" : __DIR__"caohai1",
	]));
        set("outdoor","ѩɽ");
        set("objects", ([__DIR__"npc/jqbing" : 2,]));
	set("coor/x",-310);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}

// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "��ڷ�");
	set("long", @LONG
λ��̩���س��Ա�Լһ��˴��ǵ�̩ɽ����ڡ��ഫ�����
ϼԪ����������ϷŪ������Ͷ���廨Ь�Զ�̩ɽ�ؽ磬�����ϼԪ
��ֻ�ܰ��廨Ь��ɽ�������˴����Ӵ�̩ɽ���Դ�Ϊ��㡣
LONG
	);

        set("objects", ([
		__DIR__"npc/shangren" : 1,
	]));

	set("exits", ([
		"northup" : __DIR__"baihe",
   "east" :"/d/sld/xiaolu",
        "west" : "/d/huanghe/huanghe5",
		"south" : __DIR__"yidao3",
	]));


	set("outdoors", "taishan");
	set("coor/x",170);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",170);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}


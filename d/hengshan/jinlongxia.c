// Room: /d/hengshan/jinlongxia.c

inherit ROOM;

void create()
{
	set("short", "����Ͽ");
	set("long", @LONG
����Ͽ�ֳ��������ǽ����ɽ����ڡ���ɽһ��̫��ɽ�����
�������������еı�����������֮Ϊ "����С����" ������ب����
�����һ���н��еĶ��У�������Ϊ "��ɽ����" ����� "̩ɽ
����" ��"��ɽ����"��"��ɽ����"��"��ɽ���"��
LONG
	);
	set("exits", ([
                "southeast"  : "/d/huanghe/tumenzi",
                "southwest"  : __DIR__"cuipinggu1",
	]));
	set("objects", ([
		__DIR__"npc/jing" : 1,
	]));
        set("outdoors", "��ɽ");
	set("coor/x",50);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}


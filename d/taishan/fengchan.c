// Room: /d/taishan/.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "����̨");
	set("long", @LONG
��������ʱ��ѡ�����书��һ��֮������·Ӣ������սʤ������ͨ������
�ɳ�Ϊͳ����ԭ���ֵ����䡣��̨�ϰڷ��ź���������̨�ϸ߸�����һ���죬
���飺�����е���
LONG
	);

	set("exits", ([
		"down" : __DIR__"yuhuang",
	]));

	set("objects",([
     "/clone/npc/zhong-shentong" :1,
             __DIR__"npc/wei-shi1": 2,
	]));

        set("no_clean_up", 1);
	set("outdoors", "taishan");

	set("coor/x",170);
  set("coor/y",220);
   set("coor/z",120);
   setup();
}

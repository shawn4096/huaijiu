// Room: liuzz.c
// Looklove y2k/4/26

inherit ROOM;

void create()
{
        set("short","������");
        set("long", @LONG
��ӭ����������������Ӳ��󣬵�����������ȴ������������Ϊ�����
����ס��һλ�����������ҽ������̸�������������϶��鲻�Խ�¶���Ժ���
��ɫ��������һ��С�ƹݣ�������������һ��С�ӡ�
LONG
        );

        set("exits", ([
          "south" : __DIR__"xlu_lzz",
          "north" : __DIR__"xiaohe",
          "west" : __DIR__"jiuguan",
        ]));
 
        set("coor/x",-40);
  set("coor/y",20);
   set("coor/z",0);
   setup();
}


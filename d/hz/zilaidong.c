// /u/beyond/hz/zilaidong.c ������
 
inherit ROOM;
void create()
{
        set("short","������");
        set("long", @LONG
��������ǰɽ�ֺ�ͤѭ�����ɽ����������¡�������ʹ������͵�
������������ǰ�ɸ���ɽ�µġ����������˵��������λʵ���ν������
�ļ��ÿ�괺�����ʵ�������ٹٵ��˼������Ա�ʾ��ũҵ�����ӡ�
LONG
        );
        set("exits", ([
            "north" : __DIR__"yuhuangshan",
            "southup" : __DIR__"shanlu2",
                        
]));
        set("coor/x",100);
  set("coor/y",-360);
   set("coor/z",0);
   setup();
}

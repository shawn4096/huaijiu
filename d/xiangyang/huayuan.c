//huayuan.c
//Csl 2000.04.26

inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long",@LONG
�����԰��Ȼ���󣬵�����ľ�����������ֲ�Ÿ�ʽ�����Ļ����ݲݣ���
�ĳ��������������һ�����򣬳�����������ɢ�����������������Ļ�������
��ͨ���Ժ��
LONG
        );
        set("exits",([
                "south"  :  __DIR__"houyuan",
                ]));

        set("coor/x",-60);
  set("coor/y",80);
   set("coor/z",0);
   setup();
}

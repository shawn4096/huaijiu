// miehuo2.h Cht@SJ 2000-3-12 �޸�
#include <ansi.h>
int do_miehuo(string arg)
{
        object me, ob;
        object *inv;
        me = this_object();
        ob = this_player();
        inv = deep_inventory(me);
        if( ob->is_busy())
                return notify_fail("����æ���ء�\n");
        if( ob->is_fighting())
                return notify_fail("������ս����\n");
        if( !sizeof(inv))
                return notify_fail("¯������û�ж�����\n");
        if( me->query("marks/open") )
                return notify_fail("¯���������أ�Ϲ��ʲô��\n");
        if( !me->query("marks/doing") && !me->query("marks/fired") )
                return notify_fail("¯�ӻ�û���\n");
        if( !ob->query_temp("doing", 1) )
                return notify_fail("��û�ڰ�ҩ��\n");
        if( !ob->query_temp("done", 1) )
                return notify_fail("�㻹û����ҩ�أ�\n");

        message_vision("\n$N�ѵ�¯�ڵĲ�𽥽���Ϩ���ˡ�\n", ob);
        remove_call_out("do_drug");
        remove_call_out("do_check");
        remove_call_out("do_ready");
        remove_call_out("do_confirm");
        remove_call_out("do_failed");
        if( random(300)>(int)ob->query_skill("liandan-shu",1) ) {
                call_out("do_drug3",1,me);
                me->delete("marks/aoyao");
                me->delete("marks/burned");
                me->delete("marks/doing");
                ob->start_busy(5);
                message_vision(HIR"\n��⣡����$N���������ղ�����ҩ���������������ˡ�\n"NOR,ob);
                return 1;
        }
        call_out("do_drug", 1 , me);
        me->delete("marks/aoyao");
        me->delete("marks/burned");
        me->delete("marks/doing");
        ob->start_busy(5);
        return 1;

}

void do_drug()
{
        int a, b, c, i, z;
        object obj, *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        a = 0;
        b = 0;
        c = 0;
        i = 0;
        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        if( inv[i]->name() == HIW"�չ�"NOR)
                        {
                                a = a+1;
                         }
                        if( inv[i]->name() == HIC"ľ��"NOR)
                        {
                                b = b+1;
                         }
                        if( inv[i]->name() == HIG"��ũ��"NOR)
                        {
                                c = c+1;
                         }
                         if( (int)ob->query_temp("done", 1) == 1)
                         {
                                z = 1;
                         }
                }

// ��������ɢ
                if(  sizeof(inv) != 3
                ||  a != 1
                ||  b != 1
                ||  c != 1
                ||  z != 1)
                {
                 remove_call_out("do_drug1");
                 call_out("do_drug1", 0, me);
                }

                else
                {
                        for(i=0; i<sizeof(inv); i++)
                        {      destruct(inv[i]);   }
                obj=new("/clone/medicine/wangyou-san");
                obj->move(ob);
                message_vision(YEL"\n$NС������شӵ�¯��ȡ��һ����������ɢ��\n"NOR, ob);
                remove_call_out("do_over");
                call_out("do_over", 0, obj);
                }
        }
        return;
}

void do_drug1()
{
        int a, b, c, i, z;
        object obj, *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        a = 0;
        b = 0;
        c = 0;
        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        
                        if( inv[i]->name() == HIC"ľ��"NOR)
                        {
                                a = a+1;
                         }
                        if( inv[i]->name() == GRN"������"NOR)
                        {
                                b = b+1;
                         }
                        if( inv[i]->name() == HIG"��ũ��"NOR)
                        {
                                c = c+1;
                         }
                         if( (int)ob->query_temp("done", 1) == 1)
                         {
                                z = 1;
                         }
                }

// ���Ľⶾ��
                if(  sizeof(inv) != 3
                ||  a != 1
                ||  b != 1
                ||  c != 1
                ||  z != 1)
                {
                 remove_call_out("do_drug2");
                 call_out("do_drug2", 0, me);
                }
                else
                {
                        for(i=0; i<sizeof(inv); i++)
                        {      destruct(inv[i]);   }
                obj=new("/clone/medicine/jiedu-dan");
                obj->move(ob);
                message_vision(YEL"\n$NС������شӵ�¯��ȡ��һ�����Ľⶾ����\n"NOR, ob);                                                                 
                remove_call_out("do_over");
                call_out("do_over", 0, obj);
                }
        }
        return;
}

void do_drug2()
{
        int a, b, c, i, z;
        object obj, *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        a = 0;
        b = 0;
        c = 0;
        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        
            if( inv[i]->name() == GRN"������"NOR)
                        {
                                a = a+1;
                         }
            if( inv[i]->name() == HIR"С�컨"NOR)
                        {
                                b = b+1;
                         }
            if( inv[i]->name() == HIG"��ũ��"NOR)
                        {
                                c = c+1;
                         }

            if( (int)ob->query_temp("done", 1) == 1)
                         {
                                z = 1;
                         }
                }

// �׻�������
                if(  sizeof(inv) != 3
                ||  a != 1
                ||  b != 1
                ||  c != 1
                ||  z != 1)
                {
                 remove_call_out("do_drug3");
                 call_out("do_drug3", 0, me);
                }
                else
                {
                        for(i=0; i<sizeof(inv); i++)
                        {      destruct(inv[i]);   }
                obj=new("/clone/medicine/duoming-wan");
                obj->move(ob);
                message_vision(YEL"\n$NС������شӵ�¯��ȡ��һ�Ű׻������衣\n"NOR, ob);        
                remove_call_out("do_over");
                call_out("do_over", 0, obj);
                }
        }
        return;
}

void do_drug3()
{
        int i;
        object *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        destruct(inv[i]);
                }
                message_vision(HIR"\n����ҩ������$N����ʧ���ˡ�\n"NOR,ob);
                ob->delete_temp("doing");
                ob->delete_temp("done");
                message_vision(BLU"\n��ͯ�����ְ˽ŵĴ�ͭ���в���һЩ�յĽ��ڵ�ҩ���������ע����ˮ��ϴ��\n"+
                               "$Nһ�����ԣ�����������������\n"NOR, ob);
                if( userp(ob) ) log_file("LIAN_DAN",
                sprintf("%s %s(%s) ��Ϊҩ����������ʧ�� �� %s\n", ob->query("title"), ob->name(1), geteuid(ob), ctime(time())[4..19] ) );
                me->delete("marks/fired");
                me->delete("liquid/remaining");
                me->delete("liquid/name");
        }
        return;
}

void do_over(object obj)
{       
        object me = this_object();
        object ob = this_player();

        ob->delete_temp("doing");
        ob->delete_temp("done");
        me->delete("marks/fired");
        me->delete("liquid/remaining");
        me->delete("liquid/name");   

        if( userp(ob) ) log_file("LIAN_DAN",
        sprintf("%s %s(%s)����%s(%s) �� %s\n", ob->query("title"), ob->name(1), geteuid(ob), obj->name(1), obj->query("id"), ctime(time())[4..19] ) );

        return;
}

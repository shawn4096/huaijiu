// kuloutou.c ����ͷ
// Last modify by Yanyang because erroneous word

inherit ITEM;

void create()
{
        set_name("����ͷ", ({ "kulou tou", "kulou", "tou" }) );
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 20);
                set("long", "����һ����ͷ���ú��γɵ�����ͷ�����������ָ������������ɭɭ�ġ�\n");
        }
        setup();
}

void init()
{
    add_action("do_cha",({"cha","insert"}));
}

int do_cha(string arg)
{
    object me=this_player();
if(!arg) return 0;
if (arg!="kulou" && arg!="kulou tou" && arg!="����ͷ" && arg!="����" && arg!="tou")
        return 0;
    if( me->is_fighting() || me->is_busy() )
        return notify_fail("����æ���ء�\n");
    if( me->query_skill("claw", 1) > 100)
             return notify_fail("�㷢������ô��Ҳû�����ˡ�\n");
if( (int)me->query_skill("claw",1) >= 180 && me->query("potential")>0 ){
        me->add("jing", -(20 + random(40)));
        me->add("jingli", - random(40));
        me->add("shen", -random(180));
        message_vision("$N�������ָ��������ͷ�ϵ����ָ�ס�\n", me);
        tell_object(me, "���Ȼ���������ָ���ò����ָ�ף����ﲻ�������ز���һ��а�\n");
        me->improve_skill("claw", random((int)me->query_int())+(int)me->query_skill("claw"));
 me->add("potential",-2-random(2));
if( !(me->query("potential")>0)) 
me->set("potential",0);
        if( !random(30) ) 
            call_out("destroying", 1, this_object(), me);
        return 1;
    }
    if( (int)me->query_skill("claw",1) >= 50 ) {
        message_vision("$N��������ͷ�ϵ����ָ�ף�������˼��\n", me);
        tell_object(me, "���Ȼ�����Լ��ƺ���Ӧ����ôа��\n");
        return 1;
    }
    me->add("jing", -(20 + random(40)));
    me->add("jingli", - random(40));
    me->add("shen", -random(80));
    me->improve_skill("claw", (int)me->query_int()+random((int)me->query_skill("claw")));
    message_vision("$N�������ָ��������ͷ�ϵ����ָ�ס�\n", me);
    tell_object(me, "���Ȼ���������ָ���ò����ָ�ף�����ʲôҧ��һ�£�����һ������\n");
    return 1;
}

void destroying(object obj, object me)
{     
    tell_object(me, "�������ָ�ݺݽо�����������ͷ�����������ˡ�\n");
    message_vision("$N��ָ�о���ֻ����һ�����죬��������ͷ����$N����÷��顣\n", me);
    destruct(obj);
    return;
}     

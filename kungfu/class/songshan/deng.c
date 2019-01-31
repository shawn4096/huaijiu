#include <ansi.h>
inherit NPC;

int do_ask1();
int do_ask2();
int do_ask3();

void create()
{
        set_name("�˰˹�", ({ "deng bagong", "deng", "bagong" }));
        set("nickname", HIC"���"NOR);
        set("long", "����һ�����������ߣ�һ����������ĳ����뻯��\n");
        set("gender", "����");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("no_get", "�˰˹�������˵̫���ˡ�\n");
        set("unique", 1);
        
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 2000000);
        set("eff_neili", 4000);
        set("shen", -15000);

    set_skill("force", 180);
    set_skill("hanbing-zhenqi", 180);
    set_skill("dodge", 180);
    set_skill("zhongyuefeng", 180);
    set_skill("hand", 180);
    set_skill("songyang-shou", 180);
    set_skill("parry", 180);
//  set_skill("whip", 180);
//  set_skill("songyang-bian", 180);
    set_skill("sword", 180);
    set_skill("songshan-jian", 180);
    set_skill("literate", 100);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("hand", "songyang-shou");
    map_skill("parry", "songshan-jian");
    map_skill("sword", "songshan-jian");
//  map_skill("whip", "songyang-bian");
    prepare_skill("hand", "songyang-shou");
    create_family("��ɽ��", 4, "����");
    set("chat_chance_combat", 10);
    set("chat_msg_combat", ({
                (: perform_action, "sword.feiwu" :),
        }));
        set("inquiry", ([
                "name": (: do_ask1() :),
                "���": (: do_ask2() :),
                "���ɱ�": (: do_ask3() :),
        ]));
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
        carry_object(BINGQI_D("changjian"))->wield();   
}

int do_ask1()
{
        object me = this_player();
        
        command("look " + me->query("id"));
    if (me->query_skill("hanbing-zhenqi",1) < 150 || !me->query_temp("ss/zsb_0"))
        {
                command("say "+RANK_D->query_respect(me)+"����Щ��������ò�Ҫ�Ҵ�����");
                return 1;
        }
        command("nod " + me->query("id"));
        command("say ����ޡ����Ǵ�ү���ˣ���������Ӣ�ۣ����ӵı޷������ܼ���");
        me->delete_temp("ss/zsb_0");
        me->set_temp("ss/zsb_1",1);
        return 1;
}

int do_ask2()
{
        object me = this_player();
        
    if (me->query_skill("hanbing-zhenqi",1) < 150 || !me->query_temp("ss/zsb_1"))
        {
                command("say "+RANK_D->query_respect(me)+"����Щ��������ò�Ҫ�Ҵ�����");
                return 1;
        }
        command("hehe");
        command("say �뵱����һ�����ɱ޴����£�����������š���ޡ���");
        me->delete_temp("ss/zsb_1");
        me->set_temp("ss/zsb_2",1);
        return 1;
}

int do_ask3()
{
        object me = this_player();
        
    if (me->query_skill("hanbing-zhenqi",1) < 150 ||  !me->query_temp("ss/zsb_2"))
        {
                command("say "+RANK_D->query_respect(me)+"����Щ��������ò�Ҫ�Ҵ�����");
                return 1;
        }
        command("consider");
        command("whisper " + me->query("id") + " �������ɱ޵���һ��С�ĵ���Ͽ�����ˣ�\n�����ȥ��ɽ�������ң�˵�����ܷ��֡�����");
        me->delete_temp("ss/zsb_2");
        me->set_temp("ss/zsb_3",1);
        return 1;
}

void attempt_apprentice(object ob)
{
        if (ob->query("family") && ob->query("family/family_name") != "��ɽ��")
        {
                command("say "+RANK_D->query_respect(ob)+"�Ѿ���"+ ob->query("family/family_name")+"���ӣ���������������Ϊͽ��"); 
                return;
        }
        if (ob->query_skill("hanbing-zhenqi",1) < 140)
        {
                command("say "+RANK_D->query_respect(ob)+"�Ѿ���"+ ob->query("family/family_name")+"���ӣ���������������Ϊͽ��"); 
                return;
        }
        command("say �ðɣ����������������ѧ���հɡ�");
        command("recruit " + ob->query("id"));
}

int accept_object(object who, object ob)
{
        mapping fam;

        if (ob->query("id") != "zisong bian" && who->query("ss/pass_deng"))
	   {
                command("say ��������������ʲô?\n");
                return 0;
	   } 

        call_out("destroy",1,ob);

        if (!(fam = who->query("family")) || fam["family_name"] != "��ɽ��")
	   {
                command("angry "+who->query("id"));
                command("say �ⶫ����ô�ᵽ������ģ�");
                return 1;
	   }

        message_vision("�˰˹��������ɱޣ�������¶���������Ц�ݡ�\n",who);
        message_vision("�˰˹�������$N��ͷ��˵������Ȼ����Ұ����ɱ��һ����ˣ��Ҿ�ָ��ָ������ɽ�����İ���ɡ�\n",who);

	if(random(15)==1)
	   {
                tell_object(who,HIY"�㾭���˰˹��Ľ̻�󣬿����Ѿ���ȫ���Խ���ɽ�������������ˣ�\n"NOR);
                who->set("ss/pass_deng",1);
                log_file("quest/pass_deng", sprintf("%s(%s) ʧ��%d����ȫ������ɽ���������飺%d��\n", who->name(1),who->query("id"), who->query("deng_fail"),who->query("combat_exp")) );
	   }
        else
	   {
                tell_object(who,HIY"�����˵˰˹���ָ�㣬����ɽ�����İ���ȫȻ����Ҫ�졣\n\n"NOR);
                command("sigh "+who->query("id"));
                who->add("deng_fail",1);   		   
	   }
        return 1;
}

void destroy(object ob)
{
        destruct(ob);
}


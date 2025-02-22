#include <ansi.h>
inherit NPC;

int do_ask1();
int do_ask2();
int do_ask3();

void create()
{
        set_name("邓八公", ({ "deng bagong", "deng", "bagong" }));
        set("nickname", HIC"神鞭"NOR);
        set("long", "这是一名瘦削的老者，一手嵩阳鞭舞的出神入化。\n");
        set("gender", "男性");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("no_get", "邓八公对你来说太重了。\n");
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
    create_family("嵩山派", 4, "弟子");
    set("chat_chance_combat", 10);
    set("chat_msg_combat", ({
                (: perform_action, "sword.feiwu" :),
        }));
        set("inquiry", ([
                "name": (: do_ask1() :),
                "神鞭": (: do_ask2() :),
                "紫松鞭": (: do_ask3() :),
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
                command("say "+RANK_D->query_respect(me)+"，这些事情你最好不要乱打听。");
                return 1;
        }
        command("nod " + me->query("id"));
        command("say “神鞭”就是大爷我了，环顾天下英雄，老子的鞭法无人能及！");
        me->delete_temp("ss/zsb_0");
        me->set_temp("ss/zsb_1",1);
        return 1;
}

int do_ask2()
{
        object me = this_player();
        
    if (me->query_skill("hanbing-zhenqi",1) < 150 || !me->query_temp("ss/zsb_1"))
        {
                command("say "+RANK_D->query_respect(me)+"，这些事情你最好不要乱打听。");
                return 1;
        }
        command("hehe");
        command("say 想当年我一条紫松鞭打天下，江湖人送外号“神鞭”！");
        me->delete_temp("ss/zsb_1");
        me->set_temp("ss/zsb_2",1);
        return 1;
}

int do_ask3()
{
        object me = this_player();
        
    if (me->query_skill("hanbing-zhenqi",1) < 150 ||  !me->query_temp("ss/zsb_2"))
        {
                command("say "+RANK_D->query_respect(me)+"，这些事情你最好不要乱打听。");
                return 1;
        }
        command("consider");
        command("whisper " + me->query("id") + " 那条紫松鞭当年一不小心掉入峡谷中了！\n你可以去嵩山脚下找找，说不定能发现。。。");
        me->delete_temp("ss/zsb_2");
        me->set_temp("ss/zsb_3",1);
        return 1;
}

void attempt_apprentice(object ob)
{
        if (ob->query("family") && ob->query("family/family_name") != "嵩山派")
        {
                command("say "+RANK_D->query_respect(ob)+"已经是"+ ob->query("family/family_name")+"弟子，在下怎敢再收你为徒？"); 
                return;
        }
        if (ob->query_skill("hanbing-zhenqi",1) < 140)
        {
                command("say "+RANK_D->query_respect(ob)+"已经是"+ ob->query("family/family_name")+"弟子，在下怎敢再收你为徒？"); 
                return;
        }
        command("say 好吧，你就暂且在我手下学武艺吧。");
        command("recruit " + ob->query("id"));
}

int accept_object(object who, object ob)
{
        mapping fam;

        if (ob->query("id") != "zisong bian" && who->query("ss/pass_deng"))
	   {
                command("say 你给我这个东西干什么?\n");
                return 0;
	   } 

        call_out("destroy",1,ob);

        if (!(fam = who->query("family")) || fam["family_name"] != "嵩山派")
	   {
                command("angry "+who->query("id"));
                command("say 这东西怎么会到你手里的！");
                return 1;
	   }

        message_vision("邓八公看了紫松鞭，脸上逐渐露出了满意的笑容。\n",who);
        message_vision("邓八公拍了拍$N的头，说到：既然你帮我把紫松鞭找回来了，我就指点指点你嵩山剑法的奥妙吧。\n",who);

	if(random(15)==1)
	   {
                tell_object(who,HIY"你经过邓八公的教诲后，看来已经完全可以将嵩山剑法运用自如了！\n"NOR);
                who->set("ss/pass_deng",1);
                log_file("quest/pass_deng", sprintf("%s(%s) 失败%d次完全掌握嵩山剑法。经验：%d。\n", who->name(1),who->query("id"), who->query("deng_fail"),who->query("combat_exp")) );
	   }
        else
	   {
                tell_object(who,HIY"你听了邓八公的指点，对嵩山剑法的奥妙全然不得要领。\n\n"NOR);
                command("sigh "+who->query("id"));
                who->add("deng_fail",1);   		   
	   }
        return 1;
}

void destroy(object ob)
{
        destruct(ob);
}


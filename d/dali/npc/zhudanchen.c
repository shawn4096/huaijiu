// zhudanchen.c add some word for auto update.
// by cool 98.3.25
// Modify By River 98/11
#include <ansi.h>

inherit NPC;

string ask_job();

void create()
{
        set_name("朱丹臣", ({ "zhu danchen", "zhu", "danchen" }));
        set("title", "大理国镇南王府家将");
        set("gender", "男性");
        set("age", 33);
        set("str", 27);
        set("dex", 26);
        set("long", "这人身穿军服，却是一副书生模样，手里拿着两枝判官笔。\n");
        set("combat_exp", 400000);
        set("shen_type", 1);
        set("unique", 1);
        set("no_bark",1);
        set("attitude", "peaceful");
        set("no_get", "朱丹臣对你来说太重了。\n");

        set_skill("strike", 90);
        set_skill("qiantian-yiyang", 100);
        set_skill("tianlong-xiang", 100);
        set_skill("qingyan-zhang", 80);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);
        map_skill("force", "qiantian-yiyang");
        map_skill("strike", "qingyan-zhang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "qingyan-zhang");
        prepare_skill("strike","qingyan-zhang");



        set("max_qi", 900);
        set("max_jing", 500);
        set("eff_jingli", 500);
        set("neili", 900); 
        set("max_neili", 900);
        set("jiali", 20);
        set("inquiry",([
            "巡城" : (: ask_job :),
        ]));

        setup();
        carry_object(__DIR__"obj/zipao")->wear();
}

void init()
{
        add_action("do_task","task");
}

string ask_job()
{
        object ob;
        ob=this_player();
        
        if (!ob->query_temp("dali_join"))
           return RANK_D->query_respect(ob) + 
                "，你不是本王府随从，此话从何说起？";
        if (ob->query_temp("xuncheng"))
           return ("你不是已经领了巡城的任务吗？还不快去做。\n");
        if (ob->query("combat_exp") < 3000)
           return ("你武功太低，无法胜任!。\n");
        if (ob->query("combat_exp") >= 100000)
           return ("我看你的武功已有相当的功底了，就不用在我这里干事了。\n");
        ob->set_temp("xuncheng",1);
        ob->delete("job_name");
        ob->clear_condition("job_busy");
        ob->apply_condition("dali_xuncheng2",random(5)+5);
        return "好吧，你就在大理城周围四处查看一下，巡城时应当小心防范，防止外敌。";
}

int do_task(string arg)
{
        object ob, me;
        int pot, exp, sil;

        ob = this_player();
        me = this_object();

        if(!(arg||arg=="ok")) return 0;
        if(!ob->query_temp("xuncheng")) 
            return notify_fail("你没巡城跑来领什么功？\n");
        if (interactive(ob)
         && (int)ob->query_condition("dali_xuncheng2")) {
            command("angry "+ob->query("id"));
            return notify_fail(RED"你这么快回来了，是不是有些地方只是马马虎虎看看？\n"NOR);
            }          
        if(!(ob->query_temp("dali_xc/xueshan")
         && ob->query_temp("dali_xc/tianchi2")
         && ob->query_temp("dali_xc/yuelong")
         && ob->query_temp("dali_xc/ylf1")))
            return notify_fail("你是不是偷懒，城西漏了些地方没巡？ \n");
        if(!(ob->query_temp("dali_xc/anning")
         && ob->query_temp("dali_xc/dg3")
         && ob->query_temp("dali_xc/xishuang")
         && ob->query_temp("dali_xc/hg2")
         && ob->query_temp("dali_xc/hg3")))
            return notify_fail("你是不是偷懒，城南漏了些地方没巡？ \n");
        if(!(ob->query_temp("dali_xc/nianhuasimen")
         && ob->query_temp("dali_xc/xs2")
         && ob->query_temp("dali_xc/sl")
         && ob->query_temp("dali_xc/yzh")
         && ob->query_temp("dali_xc/ydxxxxxx")))
            return notify_fail("你是不是偷懒，城东漏了些地方没巡? \n");
        if(!(ob->query_temp("dali_xc/caifeng")
         && ob->query_temp("dali_xc/chaguan")
         && ob->query_temp("dali_xc/xiulou")
         && ob->query_temp("dali_xc/chouduan")
         && ob->query_temp("dali_xc/xiyuan")
         && ob->query_temp("dali_xc/yanzhi")
         && ob->query_temp("dali_xc/datiepu")
         && ob->query_temp("dali_xc/shudian")
         && ob->query_temp("dali_xc/dafujia")
         && ob->query_temp("dali_xc/zahuopu")
         && ob->query_temp("dali_xc/shuyuan")
         && ob->query_temp("dali_xc/huadian")
         && ob->query_temp("dali_xc/yaopu")
         && ob->query_temp("dali_xc/dangpu")
         && ob->query_temp("dali_xc/yanju")
         && ob->query_temp("dali_xc/duchang")
         && ob->query_temp("dali_xc/qian")
         && ob->query_temp("dali_xc/kedian")
         && ob->query_temp("dali_xc/yizhan")
         && ob->query_temp("dali_xc/mafang")))
            return notify_fail("你是不是偷懒，城内漏了些地方没巡? \n");
        if(arg=="ok"){
            command("pat "+ob->query("id"));
            command("say 哈哈，真难为你了，"+RANK_D->query_respect(ob)+"，你做得好！");
         sil=(int)(ob->query_skill("force",1)/10)+random(5);

         if( ob->query_temp("multi_login")) sil = 1;

         exp=random(15)+ob->query("max_pot")/2;
        pot = 30+random(15);
         me->add_money("silver",sil);
         command("give "+ob->query("id")+" "+sil+" silver");
         ob->add("potential",pot);
        if(ob->query("potential") > ob->query("max_pot")) 
         ob->set("potential", ob->query("max_pot"));
         ob->add("combat_exp",exp);
         ob->add("dali_job",1);
         tell_object(ob,HIW" 你被奖励了：\n" + 
            chinese_number(exp) + "点实战经验\n" +
            chinese_number(pot) + "点潜能\n"+
            chinese_number(sil)+"两白银\n"+
             "你为镇南王府做了"+ob->query("dali_job")+"次工作。\n"NOR);
         ob->delete_temp("xuncheng");
         ob->delete_temp("dali_xc");
         return 1;
         }
     return 0;
}

<?php

namespace AppBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;

class ConcertController extends Controller
{
    private function createConcertInfo($date, $time, $place, $ava)
    {
        return array('date' => $date, 'time' => $time, 'place' => $place, 'available' => $ava);
    }

    /**
     * @Route("/concert/")
     */
    public function IndexAction()
    {
        $items = array();
        $imtes[] = $this->createConcertInfo('2015年5月3日', '14:00', '東京文化会館', false);
        $imtes[] = $this->createConcertInfo('2015年7月12日', '14:00', '鎌倉芸術館', true);
        $imtes[] = $this->createConcertInfo('2015年9月20日', '15:00', '横浜みなとみらいホール', true);
        $imtes[] = $this->createConcertInfo('2015年11月8日', '15:00', 'よこすか芸術劇場', false);
        $imtes[] = $this->createConcertInfo('2016年1月10日', '14:00', '渋谷公会堂', true);

        return $this->render('Concert/index.html.twig', array('concertList' => $imtes));
    }
}

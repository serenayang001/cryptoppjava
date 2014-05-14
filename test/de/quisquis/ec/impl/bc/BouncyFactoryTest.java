/* (C) 2014 Peter Conrad
 * All rights reserved.
 */
package de.quisquis.ec.impl.bc;

import de.quisquis.ec.AbstractFactoryTest;

import org.junit.BeforeClass;

/**
 *
 * @author Peter Conrad
 */
public class BouncyFactoryTest extends AbstractFactoryTest {
    @BeforeClass
    public static void setUpClass() {
        instance = new BouncyFactory();
        AbstractFactoryTest.setUpClass();
    }
}
